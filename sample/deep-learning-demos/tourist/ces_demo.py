import classification_helper as drawing_helper
import TouristDemoHelper as driving_helper

driving_model = driving_helper.load_model("driving")
print("~driving model loaded~")
drawing_model = drawing_helper.generate_calssification_model()
print("~drawing model loaded~")

driving_helper.calibrate_motors()

while True:
    
    input("Press enter to begin!")
    
    try:
        destination = drawing_helper.predict(drawing_model)
        print("Headed to " + destination + "!")
        driving_helper.drive_to_landmark(destination, driving_model)
        
    except Exception as e:  #catch a keyboard interrupt
        print(e)