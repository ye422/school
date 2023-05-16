echo 'working directory:'

read dirname 

if [ -n "$dirname" ]

then
	cd "$dirname" || echo "Error. Can't access to the directory or Invaild directory."
	
	for dir in *
	do
		newname=$(echo $dir | tr "[a-z] [A-Z]" "[A-Z] [a-z]")
		mv $dir $newname
	done
else 
	for dir in *

	do 
		newname=$(echo $dir | tr "[a-z] [A-Z]" "[A-Z] [a-z]")
		mv $dir $newname
	done
fi
