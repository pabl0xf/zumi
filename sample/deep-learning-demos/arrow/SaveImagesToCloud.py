#python3 /home/pi/zumi/sample/deep-learning-demos/driving/SaveImagesToCloud.py --noauth_local_webserver

import TrainingDataHelper as data_helper

data_helper.upload_images_to_cloud()

# If this script gives an error that it can't find credentials.json, you should change it's permissions with chmod 777 credentials.json
