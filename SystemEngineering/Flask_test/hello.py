from flask import Flask
import os
pipe_name = 'pipefile'
if not os.path.exists(pipe_name):
	os.mkfifo(pipe_name)

pipeout = os.open(pipe_name, os.O_WRONLY)

app = Flask(__name__)

@app.route('/')
def hello_workd():
	os.write(pipeout, 'Hello World/n')
	return 'Hello World!'

if __name__ == '__main__' :
	app.run()
