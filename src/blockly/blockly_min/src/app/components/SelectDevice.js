import React, { Component } from "react";
import ReactDOM from "react-dom";

class SelectDevice extends React.Component {
  componentDidMount() {
    this.state = { typeDevice: "codrone" };
    this.handleChange = this.handleChange.bind(this);
  }

  handleChange(el) {
    global.DEVICE_TYPE = el.target.value;
    if(global.DEVICE_TYPE === 'zumi') {
      $(".buttonTab").removeClass("active");
      $('#juniorXmlBtn').addClass("active");
      var toolboxText = document.getElementById("juniorZumiXml").outerHTML;
      var toolboxXml = Blockly.Xml.textToDom(toolboxText);
      $(".blocklyToolboxDiv").attr("role", "junior");

      Code.workspace.updateToolbox(toolboxXml);
      Code.addClassToCategories();
    }
    else{
      $( '#juniorXmlBtn' ).trigger( "click" );
    }
  }

  render() {
    const selectedOptionId = 0;
    return (
      <div style={{ height: "88px" }}>
        <select onChange={this.handleChange}>
          <option value="codrone" defaultValue={selectedOptionId}>
            CoDrone
          </option>
          <option value="zumi">Zümi</option>
        </select>
      </div>
    );
  }
}

export default SelectDevice;
