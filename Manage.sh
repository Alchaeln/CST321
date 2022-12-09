#!/bin/bash
input_file_name=$1 
group_name=$2 
operation_flag=$3 

if [ $# -ne 3 ] 
then
        echo "Invalid Arguments passed" 
		exit 1 
fi

checking_empty_lines_count=`grep -cvP '\S' ${input_file_name}` 
if [[ ${checking_empty_lines_count} -ne 0 ]] 
then
        echo "${input_file_name} is having $checking_empty_lines_count empty lines"
		sed -i '/^$/d' ${input_file_name} 
fi

if [ ${operation_flag} = "add" ] 
then 
	for i in `cat $i`; 
	do
		input_username=`echo $i | awk -F " " '{print $1}'` 
		input_password=`echo $i | awk -F " " '{print $2}'` 
		if getent group ${group_name} | grep -q "\b${input_username}\b"; then
			echo "${input_username} Already exists"
		else	
			sudo usermod -a -G ${group_name} ${input_username} 
			encry_in_pw=`echo ${input_password} | openssl enc -aes-256-cbc -a -salt -pass pass:giveyourpassword` 
			echo "${input_username} ${encry_in_pw}" >> tmp_inputfile.txt 
		fi
	done
	mv tmp_inputfile.txt ${input_file_name} 
else 
	for i in `cat $i`; 
	do
		input_username=`echo $i | awk -F " " '{print $1}'` 
		input_password=`echo $i | awk -F " " '{print $2}'`
		if getent group ${group_name} | grep -q "\b${input_username}\b"; then
			sudo gpasswd -d ${input_username} ${group_name} 
			userdel -r ${input_username}
		else	
			echo "${input_username} doesn't exists in the ${group_name}"
		fi
	done
fi
