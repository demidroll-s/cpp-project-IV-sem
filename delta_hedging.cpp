#include "delta_hedging.h"
#include "testing.h"
#include "matlib.h"
 
using namespace std;
 
Hedging_simulator::Hedging_simulator()
{
    shared_ptr<Black_Scholes_model> model(new Black_Scholes_model());
    model->stock_price = 1;
    model->date = 0;
    model->risk_free_rate = 0.05;
    model->volatility = 0.2;
    model->drift = 0.10;
 
    shared_ptr<Call_option> option = make_shared<Call_option>();
    option->set_strike(model->stock_price);
    option->set_maturity(1);
 
    set_to_hedge(option);
    set_simulation_model(model);
    set_pricing_model(model);
    n_steps = 10;
    set_n_steps(n_steps);
}

Hedging_simulator::Hedging_simulator(double maturity_, Black_Scholes_model model_, int n_steps_)
{
    shared_ptr<Black_Scholes_model> model(new Black_Scholes_model());
    model->stock_price = model_.stock_price;
    model->date = model_.date;
    model->risk_free_rate = model_.risk_free_rate;
    model->volatility = model_.volatility;
    model->drift = model_.drift;
 
    shared_ptr<Call_option> option = make_shared<Call_option>();
    option->set_strike(model->stock_price);
    option->set_maturity(maturity_);
 
    set_to_hedge(option);
    set_simulation_model(model);
    set_pricing_model(model);
    set_n_steps(n_steps_);
}

std::vector<double> Hedging_simulator::run_simulations(int n_simulations) const
{
    std::vector<double> ret(n_simulations);
    for (int i = 0; i < n_simulations; i++) 
	{
        ret[i] = run_simulation();
    }
    return ret;
}

double Hedging_simulator::run_simulation() const
{
    double T = to_hedge->get_maturity();
    double S0 = simulation_model->stock_price;
    vector<double> price_path = 
        simulation_model->generate_price_path(T,n_steps);
 
    double dt = T / n_steps;
    double charge = choose_charge(S0);
    double stock_quantity = select_stock_quantity(0,S0);
    double bank_balance = charge - stock_quantity * S0;
    for (int i = 0; i< n_steps-1; i++) {
        double balance_with_interest = bank_balance * exp(simulation_model->risk_free_rate*dt);
        double S = price_path[i];
        double date = dt * (i + 1);
        double new_stock_quantity = select_stock_quantity(date, S);
        double costs = (new_stock_quantity - stock_quantity)*S;
        bank_balance = balance_with_interest - costs;
        stock_quantity = new_stock_quantity;
    }
    double balance_with_interest = bank_balance *exp(simulation_model->risk_free_rate * dt);
    double S = price_path[n_steps - 1];
    double stock_value = stock_quantity * S;
    double payout = to_hedge->payoff(S);
    return balance_with_interest + stock_value - payout;
}
 
double Hedging_simulator::choose_charge(double stock_price) const
{
    Black_Scholes_model pm = *pricing_model;
    pm.stock_price = stock_price;
    return to_hedge->price(pm);
}

double Hedging_simulator::select_stock_quantity(double date,double stock_price) const
{
    Black_Scholes_model pm = *pricing_model;
    pm.stock_price = stock_price;
    pm.date = date;
    return to_hedge->delta(pm);
}

void test_hedging()
{
	ifstream f_input("delta-input.txt");
    ofstream f_output;
    double drift, stock_price, volatility, risk_free_rate, date, maturity, n_scenarios;
    if(f_input.is_open())
    {
        double a[7];
        int i = 0;
        while (f_input >> a[i])
            i++;
        f_input.close();
        risk_free_rate = a[0]/100;
		stock_price = a[1];
		drift = a[2];
		volatility = a[3]/100;
        date = a[4];
		maturity = a[5];
		n_scenarios = a[6];
        f_output.open("delta-output.txt");
		int n_steps = 10;
        Black_Scholes_model bsm(drift, stock_price, volatility, risk_free_rate, date);
		Hedging_simulator simulator(maturity, bsm, n_steps);
        vector<double> balance;
        balance.resize(n_scenarios);
		balance = simulator.run_simulations(n_scenarios);
        for (int i = 0; i < n_scenarios; i++)
        {
            f_output << i << " " << balance[i] << endl;
        }
        f_output.close();
        f_output.open("delta-table-simulation.txt");
            f_output << stock_price << " " << risk_free_rate * 100 << " " << volatility * 100 << " " << drift << " " << date;
        f_output.close();

		f_output.open("delta-table-pricing.txt");
            f_output << stock_price << " " << risk_free_rate * 100 << " " << volatility * 100 << " " << drift << " " << date;
        f_output.close();

		f_output.open("delta-table-option.txt");
            f_output << maturity << " " << n_steps;
        f_output.close();
        cout << "Program executed well!" << endl;
    }
    else
    {
        cout << "Unable to open file!" << endl;
        cout << "Error during program execution!" << endl;
    }
}
