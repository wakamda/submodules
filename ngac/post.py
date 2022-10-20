import requests


url = 'http://ngac.org.cn/ngcs/dataPage'

"""
search:搜索关键字,中文有问题
radio:
pageSize:显示的数量
pageNum:显示的页数
"""
data = {
    'search':'',
    'radio':'1',
    'pageSize':'10',
    'pageNum':'1'
}
x = requests.post(url, data=data)

print(x.text)