#!/usr/bin/env python
# -*- coding: utf-8 -*-
import os

from qcloud_image import Client
from qcloud_image import CIUrl, CIFile, CIBuffer, CIUrls, CIFiles, CIBuffers

# nan_appid='1255955027'
# nan_secretid='AKIDwnT9iA3caNyNbfqLJAqKdrxsdIm55URH'
# nan_secretkey='oUyY0LWQJCC81mLm3b3KPSN6e4IQNAmC'
# nan_bucket='nvrenlian'

# appid = '1255955027'
# secret_id = 'AKIDwnT9iA3caNyNbfqLJAqKdrxsdIm55URH'
# secret_key = 'oUyY0LWQJCC81mLm3b3KPSN6e4IQNAmC'
# bucket = 'nvrenlian'

appid = '1255955027'
secret_id = 'AKIDwnT9iA3caNyNbfqLJAqKdrxsdIm55URH'
secret_key = 'oUyY0LWQJCC81mLm3b3KPSN6e4IQNAmC'
bucket = 'nvrenlian'
client = Client(appid, secret_id, secret_key, bucket)
client.use_http()
client.set_timeout(30)
# def save(filename, contents):
#   fh = open(filename, 'a+')
#   fh.writelines(contents)
#   fh.close()
# file = open('names.txt','w+')
# file.truncate()
# file.close()
# input_photopath='../photos/init.jpg'
# result = client.face_identify('group1', CIFile(input_photopath))
# # value_no=80
# # value_yes=96
# for i in range(1,5):
#     person=client.face_getinfo(result['data']['candidates'][i]['person_id'])
#     person_id=person['data']['person_id']
#     person_name = person['data']['person_name']+' '
#     save('names.txt',person_name)
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
# print (client.face_getpersonids('group1'))
# for i in range(1,21):
#     print (client.face_delperson(str(i)))
# for i in range(1,18):
#     print (client.face_newperson(str(i), ['group1',], CIFile('../photos/'+'M'+str(i)+'.jpg')))
#     print (client.face_setinfo(str(i), 'M'+str(i)))
# print(client.face_getinfo('7'))
# print (client.face_getpersonids('group1'))
print (client.face_delperson('10'))
