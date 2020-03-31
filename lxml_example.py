import requests
import pandas as pd

url = 'http://www.ffiec.gov/census/report.aspx?year=2011&state=01&report=demographic&msa=11500'
html = requests.get(url).content
df_list = pd.read_html(html)
df = df_list[-1]
print(df)
df.to_csv('my data.csv')

