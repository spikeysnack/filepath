![filepath](doc/filepath.png?raw=true  "filepath")

filepath
=========

version: 1.3
---------

revision date: 04 Nov 2016
-------------

Description:
-------------

	filepath returns the full path of a file.

	If the file does not exist it returns nothing.
	
	This is useful for shell scripts  and resolving 
	symbolic links to the actual file, 

	which may have a different name.
	
	In that case the actual file name is returned.


usage:
-----
	        filepath  [ options ]      file(s)


Options:
-------
			-c	  continue through errors (default:no)

			-d	  delimit output with newline

			-D<string>  delimit output with string

			-h        print help message

			-w        print numerical error if error occurs

			-W        print textual   error if error occurs

			-v        print version and exit

Examples:
--------
               filepath  file1  file2  softlink
		       		 /path/file1 /path/file2 /actual/path/file 

		       filepath  <nonexistent file>
		       		 (no output)

		       filepath  -w <nonexistent file>  
		       		 (no output)

		       filepath  -w <nonexistent file> file 
		       		 /path/file

		       filepath  -W <file1> <nonexistent file> <file2>  
		       		 /path/file1 No such file or directory (program quits)

		       filepath  -W -c file1 <nonexistent file> file2   
		       		 /path/file1 No such file or directory /path/file2 

		       filepath /etc/passwd
		       		(no output)

		       filepath -w /etc/passwd
		       		13

		       filepath -W /etc/passwd
		       		access denied
		       
		       filepath -d *
		       		/path/file1
		       		/path/file2
		       		...
				
		       filepath -D" : "  *
		       		/usr/local/src/file_1 : /usr/local/src/file_2 : /usr/local/src/file_3



Files:
------
		       /usr/local/bin/filepath		           program binary

		       /usr/local/share/man/man1/filepath.1        man page 

		       /usr/local/share/doc/filepath/		   documentation 

See also:
---------
			*realpath* (3)

Bugs:
-----
			In regular and numerical warning (-w) mode filepath ignores
				**ENOENT** (error 2  -- file not found)
				**EINVAL** (error 22 -- Invalid argument)


			This is intentional. It helps  integration with shell scripts.
			Shells already have facilities for those condtions.


Author:
-------
			Chris Reid <spikeysnack@gmail.com>

Copyright:
----------
			@2016-2020 free for non-commercial use.




