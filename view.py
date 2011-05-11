#!/usr/bin/python

import json

data = []
for line in open('build/.ninja_log'):
    if line.startswith('#'):
        continue
    start, end, target, _ = line.split(' ', 3)

    data.append({
            'start': int(start),
            'end': int(end),
            'target': target
            })

data.sort(key=lambda row: row['start'])

print 'var data =', json.dumps(data), ';'
