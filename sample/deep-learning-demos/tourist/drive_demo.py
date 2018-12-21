import TouristDemoHelper as tourist_demo
model = tourist_demo.load_model("landmark")

tourist_demo.set_speed(30)
tourist_demo.drive_to_landmark("china", model)