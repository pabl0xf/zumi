import 'babel-polyfill';
import React, { Component } from "react";
import ReactDOM from "react-dom";
import './code.js';
import './commons/utils.js';
import './lib/interfaces/flight.js';
import './lib/interfaces/sequences.js';
import './lib/interfaces/flyVariables.js';
import './lib/interfaces/lights.js';
import './lib/interfaces/sensors.js';
import './lib/interfaces/statusCheckers.js';
import './lib/interfaces/events.js';

import ConnectionBox from './components/connectionBox/ConnectionBox.js';
import Burger from './components/menu/Menu.js';
import ContentTutorials from './components/panel/ContentTutorials.js';
import Panel from './components/panel/Panel.js';
import MasterWorkspace from './components/masterWorkspace/MasterWorkspace.js';
import MasterToolbox from './components/masterToolbox/MasterToolbox.js';
import SelectDevice from './components/SelectDevice.js';

ReactDOM.render(
  <ConnectionBox />,
  document.getElementById('connectMenu')
);

ReactDOM.render(
  <SelectDevice />,
  document.getElementById('selectDevice')
);

ReactDOM.render(
  <Burger />,
  document.getElementById('burgerMenu')
);

ReactDOM.render(
  <Panel />,
  document.getElementById('panel')
);

ReactDOM.render(
  <MasterWorkspace />,
  document.getElementById('masterWorkspace')
);

ReactDOM.render(
  <MasterToolbox />,
  document.getElementById('masterXml')
);
