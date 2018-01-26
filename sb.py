#!/usr/bin/env python
# -*- coding: utf-8 -*-
import os

from qcloud_image import Client
from qcloud_image import CIUrl, CIFile, CIBuffer, CIUrls, CIFiles, CIBuffers

appid = '1255955027'
secret_id = 'AKIDwnT9iA3caNyNbfqLJAqKdrxsdIm55URH'
secret_key = 'oUyY0LWQJCC81mLm3b3KPSN6e4IQNAmC'
bucket = 'nvrenlian'

client = Client(appid, secret_id, secret_key, bucket)
client.use_http()
client.set_timeout(30)


# input_photopath='../photos/init.jpg'
# result = client.face_identify('group1', CIFile(input_photopath))
# value_no=80
# value_yes=96

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
print (client.face_delperson('18'))
# print (client.face_newperson('7', ['group1',], CIFile('7chenqiusheng.jpeg')))
# print (client.face_setinfo('7', 'chenqiusheng'))
# print(client.face_getinfo('7'))
# print (client.face_getpersonids('group1'))
