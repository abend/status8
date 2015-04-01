all:
	rsync -avh -e "ssh -x" *.stl alx@10.0.0.120:~/replicator/blink8/
