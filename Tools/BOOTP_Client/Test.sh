rm testreport.log
rm ip.txt

# User define Function (UDF)
processLine(){
  line="$@" # get all args
  #  just echo them, but you may need to customize it according to your need
  # for example, F1 will store first field of $line, see readline2 script
  # for more examples
  # F1=$(echo $line | awk '{ print $1 }')
  echo $line
}

REPORT=testreport.log

#Case 1
echo -n "./bootpc -d                  " >> "$REPORT"
./bootpc -d
if [ "$?" -eq 0 ]; then
	echo  "Success" >> "$REPORT"
else
	echo "Failure" >> "$REPORT"
fi

#Case 2
echo -n "./bootpc -h                  " >> "$REPORT"
./bootpc -h
if [ "$?" -eq 0 ]; then
	echo "Success" >> "$REPORT"
else
	echo "Failure" >> "$REPORT"
fi

#Case 3
echo -n "./bootpc -l                  " >> "$REPORT"
./bootpc -l
if [ "$?" -eq 0 ]; then
	echo "Success" >> "$REPORT"
else
	echo "Failure" >> "$REPORT"
fi

#Case 4
echo -n "./bootpc -d 192.168.3.255    " >> "$REPORT"
./bootpc -d 192.168.3.255
if [ "$?" -eq 0 ]; then
	echo "Success" >> "$REPORT"
else
	echo "Failure" >> "$REPORT"
fi

#Case 5
echo -n "./bootpc -d 999.999.999.255  " >> "$REPORT"
./bootpc -d 999.999.999.255
if [ "$?" -eq 0 ]; then
	echo "Success" >> "$REPORT"
else
	echo "Failure" >> "$REPORT"
fi

#Case 6
echo -n "./bootpc     		     " >> "$REPORT"
./bootpc
if [ "$?" -eq 0 ]; then
	echo "Success" >> "$REPORT"
else
	echo "Failure" >> "$REPORT"
fi

#Case 7
echo -n "./bootpc -dh                 " >> "$REPORT"
./bootpc -dh
if [ "$?" -eq 0 ]; then
	echo "Success" >> "$REPORT"
else
	echo "Failure" >> "$REPORT"
fi

#Case 8
echo -n "./bootpc 255.255.255.255     " >> "$REPORT"
./bootpc 255.255.255.255
if [ "$?" -eq 0 ]; then
	echo "Success" >> "$REPORT"
else
	echo "Failure" >> "$REPORT"
fi

#Case 9
echo -n "./bootpc 192.168.3.255       " >> "$REPORT"
./bootpc 192.168.3.255
if [ "$?" -eq 0 ]; then
	echo "Success" >> "$REPORT"
else
	echo "Failure" >> "$REPORT"
fi


/sbin/ifconfig eth0 | grep "inet addr:" | awk '{print$2}' | cut -b 6- >> ip.txt
FILE="ip.txt"
# make sure file exist and readable
   if [ ! -f $FILE ]; then 
  	echo "$FILE : does not exists"
  	exit 1
   elif [ ! -r $FILE ]; then
  	echo "$FILE: can not read"
  	exit 2
   fi
exec 0<$FILE
while read line
do
	# use $line variable to process line in processLine() function
	processLine $line
	
	#Case 10
	echo -n "ping -c 3" $line "     " >> "$REPORT"
	ping -c 3 $line
	if [ "$?" -eq 0 ]; then
		echo "Success" >> "$REPORT"
	else
		echo "Failure" >> "$REPORT"
	fi
done
clear
cat testreport.log


