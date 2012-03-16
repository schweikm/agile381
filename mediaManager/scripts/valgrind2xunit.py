#!/usr/bin/env python

import sys, xml.etree.ElementTree as ET

testDir = sys.argv[1]
testName = sys.argv[2]

doc = ET.parse(testDir + "/valgrind_" + testName + ".xml")
errors = doc.findall('.//error')

out = open(testDir + "/" + testName + "_valgrind.xml", "w")
out.write('<?xml version="1.0" encoding="UTF-8"?>\n')
out.write('<testsuite name="' + testName + '" tests="1" errors="0" failures="' + str(len(errors)) + '" skip="0">\n')
out.write('    <testcase name="Memory check" status="run" time="0" classname="' + testName + '">\n')
for error in errors:
        kind = error.find('kind')
        what = error.find('what')
        if  what == None: 
                what = error.find('xwhat/text')
        
        out.write('        <error type="'+kind.text+'">\n')
        out.write('            '+what.text+'\n')
        out.write('        </error>\n')
out.write('    </testcase>\n')
out.write('</testsuite>\n')
out.close()
