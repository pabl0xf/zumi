import TouristDemoHelper as tourist_demo
model = tourist_demo.load_model("landmark")

tourist_demo.speed = 40  #35 for Pumi
tourist_demo.drive_to_landmark("china", model)