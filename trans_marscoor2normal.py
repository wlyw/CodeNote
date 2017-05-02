#-*-coding:utf-8-*-
"""

"""

import collections
import csv
import json
import time
import datetime
import urllib.request
from time import ctime, sleep


if __name__ == "__main__":
    
    file_name = "datawithbd.csv"
    f = open(file_name,'a')
    write = csv.writer(f)

    count = 0
    allveh = 0
    
    with open('data.csv','r') as csvfile:
        rows=csv.reader(csvfile)
        for row in rows:
            if rows.line_num==1:
                continue
            if len(row)==0:
                continue
            allveh = allveh + 1
            
            try:
                coords=row[1]+','+row[2]
                url='http://api.map.baidu.com/geoconv/v1/?coords='+coords+'&from=1&to=5&ak=oP4ZrcK4QFAmGf0RQW8ZSGXf'
                urldata=urllib.request.urlopen(url).read()
                deurldata=urldata.decode('UTF-8')
                urljson=json.loads(deurldata)
                urljson=urljson['result']
                ur=urljson[0]
                count = count + 1
            except:
                sleep(60)
                continue
                
            bdpos = row
            bdpos[1] = ur['x']
            bdpos[2] = ur['y']
            
            write.writerow(bdpos)
            #print(bdpos)

    print(allveh)
    print(count)
    csvfile.close()
    f.close()
