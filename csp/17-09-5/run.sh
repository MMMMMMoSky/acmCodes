./tmpData > tmpData.in
cat tmpData.in | ./tmp > tmp.out
cat tmpData.in | ./tmpCmp > tmpCmp.out
diff tmp.out tmpCmp.out