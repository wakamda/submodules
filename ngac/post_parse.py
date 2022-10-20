import requests
import re
import json
from urllib import parse
import sys

# url
url = 'http://ngac.org.cn/ngcs/dataPage'

# url的参数
header ={
    'Content-Type': 'application/x-www-form-urlencoded; charset=UTF-8'
}
data = {
    'search':'',
    'radio':1,
    'pageSize':10,
    'pageNum':1
}
################################################## 修改此处 ######################################################
# s:搜索关键字，在''内修改
s = '塔里木'
# p:显示的数量
p = 10
# p:查找第几页
n = 1
################################################## end     ######################################################
data["search"] = s.encode('utf-8') 
data["pageSize"] = p
data["pageNum"] = n

# post请求，UTF-8
responce = requests.post(url, data=data, headers=header)

# 调试用
print(responce.request.headers)
print("\n")
print(responce.request.body)

# 判断请求是否成功
if responce.ok <= 0:
    print("post receive failed")
    sys.exit(0)

# 解析pageSize
pagesize = responce.json()["pageSize"]
#print(pagesize)

# 解析result，写入文件，循环执行
with open("text.txt","w") as file:
    file.write(
    "剖面名称                  矿区名称                 剖面测量单位                                地质剖面图                   比例尺    起点经度    起点纬度    终点经度    终点纬度    地质剖面   \n")

i=0
while (i < pagesize) :
    # 将responce（ojbect）先截取result(list对象),list对象可以被索引
    result_list = responce.json()["result"]
    #print(responce.json())
    #print(result_list)

    #判断result是否为空
    if len(result_list) == 0:
        print("搜索结果为空！")
        sys.exit(0)
    
    # 循环解析每个list中的元素,类型为dict字典
    each_result_list = result_list[i]

    print(each_result_list["sectionName"])
    print(each_result_list["miningAreaName"])
    print(each_result_list["company"])
    print(each_result_list["fileName"])
    print(each_result_list["scale"])
    print(each_result_list["startingLongitude"])
    print(each_result_list["startingLatitude"])
    print(each_result_list["destinationLongitude"])
    print(each_result_list["destinationLatitude"])
    print(each_result_list["geologicalSection"])
    print(each_result_list["guid"])
    print(each_result_list["personnel"])
    print(each_result_list["area"])
    



    # 写入文件
    with open('text.txt', mode='a') as file:
        file.write(
        each_result_list["sectionName"]      +"  "+
        each_result_list["miningAreaName"]      +"  "+
        each_result_list["company"]      +"  "+"http://www.ngac.org.cn/ngcsd/"+
        each_result_list["fileName"]      +"  "+
        each_result_list["scale"]      +"  "+
        each_result_list["startingLongitude"]      +"  "+
        each_result_list["startingLatitude"]      +"  "+
        each_result_list["destinationLongitude"]      +"  "+
        each_result_list["destinationLatitude"]      +"  "+
        each_result_list["geologicalSection"]      +"  "+
        each_result_list["guid"]      +"  "+
        each_result_list["personnel"]      +"  "+
        each_result_list["area"]      +"\n"
        )
    print("\n-------------------------\n")
    i = i+1


print("bye!")