import smbus
import os
import errno
import time

error = 0

bus = smbus.SMBus(1)
address = 0x04

inputIter = 0
outputIter = 0
inputBuffer = []
outputBuffer = []
bufferSize = 100

j = 0

def displayWarning(num):
	global error
	if error < 10:
		error+=1
	elif error == 10:
		if num == 0:
			print("WARNING: Zumi board not detected. Please ensure that the Zumi board is connected before using Zumi-specific functions.")
		elif num == 1:
			print("WARNING: Unknown I2C device detected at address 0x04. Please ensure that the Zumi board is connected properly, and has been updated with the latest software. If you are no longer using the Zumi Board you can disable these error messages by...")
		error+=1
	else:
		time.sleep(5)

def forwardCommand(commandLength, arg1=0, arg2=0, arg3=0, iter=0):
	try:
		if commandLength == 1:
			bus.write_byte(address, arg1)
		elif commandLength == 2:
			bus.write_byte_data(address, arg1, arg2)
		elif commandLength == 3:
			bus.write_i2c_block_data(address, arg1, [arg2, arg3])
	except IOError:
		if iter<5:
			time.sleep(0.1)
			forwardCommand(commandLength, arg1, arg2, arg3, iter)
			iter+=1

for i in range(0,bufferSize):
	inputBuffer.append(0)
	outputBuffer.append(0)

#while 1:
#	try:
#		if bus.read_byte_data(address, 0) == 10:
#			print("Zumi online. Welcome!")
#			break
#		else:
#			displayWarning(1)
#	except IOError:
#		displayWarning(0)

while 1:
	try:
		pipe = os.open('pipe', os.O_RDONLY | os.O_NONBLOCK)
		input = os.read(pipe,100)
	except OSError as err:
		if err.errno == 11:
			continue
		else:
			raise err
	if input:
		inputList = list(input)
		for i in range(0,len(inputList)):
			inputBuffer[inputIter%bufferSize] = inputList[i]
			inputIter += 1
	os.close(pipe)

	if outputIter != inputIter:
		i = inputBuffer[outputIter%bufferSize]
		if i != 10:
			outputBuffer[outputIter%bufferSize] = i
			j += 1
		else:
			if j == 1:
				forwardCommand(j, outputBuffer[(outputIter-1)%bufferSize])
			elif j == 2:
				forwardCommand(j, outputBuffer[(outputIter-2)%bufferSize], outputBuffer[(outputIter-1)%bufferSize])
			elif j == 3:
				forwardCommand(j, outputBuffer[(outputIter-3)%bufferSize], outputBuffer[(outputIter-2)%bufferSize], outputBuffer[(outputIter-1)%bufferSize])
			j = 0
		outputIter += 1
