global.PRIMARY_SERVICE = "c320df00-7891-11e5-8bcf-feff819cdc9f";
global.WRITE_CHARACTERISTIC = "c320df02-7891-11e5-8bcf-feff819cdc9f";
global.NOTIIFY_CHARACTERISTIC = "c320df01-7891-11e5-8bcf-feff819cdc9f";

global.RUNNING = false;
global.PROGRAM_IS_RUNNING = false;
global.RUN_ONLY_DISPLAY_BLOCKS = false;
global.DISPLAY_INTERVAL = false;
global.KEY_PRESSED = -1;

global.DEVICE_TYPE = 'codrone';
global.ZUMI_IMPORT_STATEMENT ='import Zumi\n\nzumi = Zumi.Zumi()\nzumi.pair(zumi.Nearest)\n\n';
global.CODRONE_IMPORT_STATEMENT = 'import CoDrone\n\ndrone = CoDrone.CoDrone()\ndrone.pair(drone.Nearest)\n\n';
global.BACKGROUND_RUNNING = false;
global.ZUMI_URL = ''


global.HOLD = { armCode: 0x41, eyeCode: 0x11 };
global.OFF = { armCode: 0x40, eyeCode: 0x10 };
global.FLICKER = { armCode: 0x43, eyeCode: 0x13 };
global.FLICKER_DOUBLE = { armCode: 0x44, eyeCode: 0x14 };

global.DIMMING = { armCode: 0x45, eyeCode: 0x15 };
global.FLOW = { armCode: 0x46, eyeCode: 0x16 };
global.REVERSE_FLOW = { armCode: 0x47, eyeCode: 0x17 };
global.MIX = { armCode: 0x42, eyeCode: 0x12 };
global.keyPressMap = {};
global.keydownCallback = null;

global.RED = "Red";
global.YELLOW = "Yellow";
global.ENTER = "Yellow";
global.ORANGE = "Orange";
global.GREEN = "Green";
global.BLUE = "Blue";
global.INDIGO = "Indigo";
global.VIOLET = "Violet";

global.TAKEOFF = 1;
global.CRASH = 2;
global.UPSIDE_DOWN = 3;
global.LOW_BATTERY = "LowBattery";

global.Direction = {
  LEFT: -1,
  RIGHT: 1,
  BACKWARD: 2,
  FORWARD: 3,
  UP: 4,
  DOWN: 5
};

global.Degree = {
  ANGLE_30: 30,
  ANGLE_45: 45,
  ANGLE_60: 60,
  ANGLE_90: 90,
  ANGLE_120: 120,
  ANGLE_135: 135,
  ANGLE_150: 150,
  ANGLE_180: 180,
  ANGLE_210: 210,
  ANGLE_225: 225,
  ANGLE_240: 240,
  ANGLE_270: 270,
  ANGLE_300: 300,
  ANGLE_315: 315,
  ANGLE_330: 330
};

global.Sequence = {
  SQUARE: 1,
  CIRCLE: 2,
  TRIANGLE: 3,
  ZIGZAG: 4,
  SWAY: 5,
  HOP: 6,
  SPIRAL: 7
};

global.displayValue = {
  getHeight: "Program stopped",
  getBatteryPercentage: "Program stopped",
  getGyroAngles: "Program stopped"
};

global.displaySingleValue = {
  getHeight: "Program stopped",
  getBatteryPercentage: "Program stopped",
  getGyroAngles: "Program stopped"
};

global.Sensors = {
  GET_HEIGHT: { value: "getHeight", displayName: "Sensors.GET_HEIGHT" },
  GET_BATTERY_PERCENTAGE: {
    value: "getBatteryPercentage",
    displayName: "Sensors.GET_BATTERY_PERCENTAGE"
  },
  GET_GYRO_ANGLES: {
    value: "getGyroAngles",
    displayName: "Sensors.GET_GYRO_ANGLES"
  },
  DEFAULT_VALUE: {
    value: "getGyroAngles",
    displayName: "Sensors.GET_GYRO_ANGLES"
  }
};

global.Mode = {
  None_: 0x00,
  OFF: 0x10,
  SOLID: 0x11,
  STROBE: 0x12,
  BLINK: 0x13,
  BLINK_DOUBLE: 0x14,
  DIMMING: 0x15,
  PULSE: 0x16,
  REVERSE_PULSE: 0x17,
  EndOfType: 0x18
};

global.Keyboard = {
  BACKSPACE: 8,
  ENTER: 13,
  SPACEBAR: 32,
  UP: 38,
  DOWN: 40,
  LEFT: 37,
  RIGHT: 39,
  _0: 48,
  _1: 49,
  _2: 50,
  _3: 51,
  _4: 52,
  _5: 53,
  _6: 54,
  _7: 55,
  _8: 56,
  _9: 57,
  a: 65,
  b: 66,
  c: 67,
  d: 68,
  e: 69,
  f: 70,
  g: 71,
  h: 72,
  i: 73,
  j: 74,
  k: 75,
  l: 76,
  m: 77,
  n: 78,
  o: 79,
  p: 80,
  q: 81,
  r: 82,
  s: 83,
  t: 84,
  u: 85,
  v: 86,
  w: 87,
  x: 88,
  y: 89,
  z: 90
};

global.SUFFIX_JUNIOR = "_junior";
global.SUFFIX_SENIOR = "_senior";
global.PREFIX_EVENTS = "on";

global.KEYPRESS_EVENT = "whenKeyPress";

global.COLORS = {
  Blue: 9,
  Green: 51,
  Indigo: 56,
  Orange: 99,
  Red: 114,
  Violet: 135,
  Yellow: 139
};
