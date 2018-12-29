from googleapiclient.discovery import build
from httplib2 import Http
from oauth2client import file, client, tools
from googleapiclient.http import MediaFileUpload
import os

store = file.Storage('hi.jpg')
creds = store.get()
if not creds or creds.invalid:
    flow = client.flow_from_clientsecrets('/home/pi/zumi/sample/deep-learning-demos/driving/credentials.json', "https://www.googleapis.com/auth/drive")
    creds = tools.run_flow(flow, store)
drive_service = build('drive', 'v3', http=creds.authorize(Http()))

cloud_folder_id = "1yEIO5GpA94a2mlQGgkGCrKjcr2v7-v0a"
local_folder_path = "/home/pi/zumi/sample/deep-learning-demos/tourist/images/"
verbose_mode = False
    
def upload_images_to_cloud():
    print("Uploading images to Cloud...")    
    for file_name in os.listdir(local_folder_path):
        if is_valid_image(file_name):
            file_metadata = {'name': file_name,
                            "parents": ['' + cloud_folder_id + '']}
            media = MediaFileUpload(local_folder_path + file_name, 
                            mimetype='image/jpeg',
                            resumable=True)
    
            created = drive_service.files().create(body=file_metadata,
                                    media_body=media,
                                    fields='id').execute()
            print (str(len(os.listdir(local_folder_path))) + " files left.")
            os.remove(local_folder_path + file_name)
            
def is_valid_image(file_name):
    return file_name.endswith(".jpg") and os.path.getsize(local_folder_path + file_name) > 0 #the image is not empty
            
def clear_images_from_cloud():
    files_to_delete = get_images_in_cloud()
    print ("Deleting " + str(len(files_to_delete)) + " image(s) from Cloud...")
    for file in files_to_delete:
        result = drive_service.files().delete(fileId=file['id']).execute()
        print("  deleted " + file['name'])
        
def clear_images_from_zumi():
    print ("Deleting image(s) from Zumi...")
    import shutil
    shutil.rmtree(local_folder_path)
    os.mkdir(local_folder_path)
    
def get_images_in_cloud():
       
    results = drive_service.files().list(
        pageSize=1000, q="parents='" + cloud_folder_id + "'", fields="nextPageToken, files(id, name)").execute()
    items = results.get('files', [])
    
    if(verbose_mode):
        if not items:
            print('No files found.')
        else:
            print('Files:')
            for item in items:
                print('{0} ({1})'.format(item['name'], item['id']))
    
    return items
    
if __name__ == '__main__':
    get_images_in_cloud()
