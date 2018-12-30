print("Zumi likes to travel! She can go to 'eiffel', 'china', or 'nyc'. ")
print("Press ctrl+C to choose a new destination. Loading will take a minute...") 

import TouristDemoHelper as tourist_demo
model = tourist_demo.load_model("landmark")
tourist_demo.calibrate_motors()

while True:
    try:
        destination = input("where would you like to go?")
        tourist_demo.drive_to_landmark(destination, model)
    except Exception as e:  #catch a keyboard interrupt
        print(e)