#!/usr/bin/env python
# -*- coding: utf-8 -*-
import os

from qcloud_image import Client
from qcloud_image import CIUrl, CIFile, CIBuffer, CIUrls, CIFiles, CIBuffers

appid = '1255955027'
secret_id = 'AKIDwnT9iA3caNyNbfqLJAqKdrxsdIm55URH'
secret_key = 'oUyY0LWQJCC81mLm3b3KPSN6e4IQNAmC'
bucket = 'nvrenlian'

c = Client(appid, secret_id, secret_key, bucket)
c.use_http()
c.set_timeout(30)

inf=c.face_detect(CIFile('../photos/init.jpg'))
gender=inf['data']['face'][0]['gender']
print(inf['data']['face'][0]['gender'])
print(type(gender))
if gender>50:
    appid = '1255955027'
    secret_id = 'AKIDwnT9iA3caNyNbfqLJAqKdrxsdIm55URH'
    secret_key = 'oUyY0LWQJCC81mLm3b3KPSN6e4IQNAmC'
    bucket = 'nvrenlian'
    client = Client(appid, secret_id, secret_key, bucket)
    client.use_http()
    client.set_timeout(30)
else:
    appid = '1255316848'
    secret_id = 'AKIDkIacaJz26vZy83qAPO7anoZ4JI3ZDrdA'
    secret_key = 'QbV9XfX8TYNvDF2auzpPjqiLjsmRr2yf'
    bucket = 'faceslib'
    client = Client(appid, secret_id, secret_key, bucket)
    client.use_http()
    client.set_timeout(30)

def save(filename, contents):
  fh = open(filename, 'a+')
  fh.writelines(contents)
  fh.close()
file = open('names.txt','w+')
file.truncate()
file.close()
input_photopath='../photos/init.jpg'
result = client.face_identify('group1', CIFile(input_photopath))
# value_no=80
# value_yes=96
for i in range(1,5):
    person=client.face_getinfo(result['data']['candidates'][i]['person_id'])
    person_id=person['data']['person_id']
    person_name = person['data']['person_name']+' '
    save('names.txt',person_name)
# person_name = person['data']['person_name']
# original_photo_name=person_id+person_name+'.jpeg'
# this_path = os.getcwd()
# original_photopath = this_path+'/'+original_photo_name
# print (input_photopath,original_photopath,person_name)
#
# confidence=result['data']['candidates'][0]['confidence']

# print(confidence)
# if confidence<value_no:
#     print("不存在该顾客")
# if value_no<=confidence<value_yes:
#     print("该顾客可能是：")
#
#     print(person_name)
# if confidence>=value_yes:
#     print('该顾客是：')
#     print(person_name)

# print(client.face_getinfo('2'))
# print (client.face_getpersonids('group2'))
# print (client.face_delperson('9'))
# print (client.face_newperson('7', ['group1',], CIFile('7chenqiusheng.jpeg')))
# print (client.face_setinfo('7', 'chenqiusheng'))
# print(client.face_getinfo('7'))
# print (client.face_getpersonids('group1'))
