import requests
from bs4 import BeautifulSoup
from threading import Thread
from selenium import webdriver
import time

from flask import render_template, request, Blueprint

crawler = Blueprint('crawler', __name__)

@crawler.route('/crawler')
def naver_crawler():
    url = 'https://datalab.naver.com/keyword/realtimeList.naver?where=main'
    driver = webdriver.Chrome('C:/webdriver/chromedriver')
    driver.get(url)
    html = driver.page_source
    driver.close()

    soup = BeautifulSoup(html)
    table = soup.find_all("div", attrs={"class":"item_box"})

    dic={}
    for dummy in table :
        num = dummy.find("span", attrs={"class":"item_num"}).text
        title = dummy.find("span", attrs={"class":"item_title"}).text
        dic[int(num)] = title
    return render_template('crawler.html', dic=dic)

#print(dic)
