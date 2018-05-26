numbers='0123456789'
brackets='()'

all_number(){
    str=$1
    str_len=${#str}
    for i in $( seq 0 ${strlen}-1 ) do
        if [ ! ${str} =~ $numbers ]; then do
            return 'no'
        done
        fi
    done
    return 'yes'
}

While read phone_number
do
    str_len=${#phone_number}
    if [ $str_len = 12 ]; then do

    done
    elif [ $str_len = 14]; then do

    done
    fi

done < $file.txt

# fool!!
