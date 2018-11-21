import React, { Component } from "react";
import ReactDOM from "react-dom";

class ContentTutorials extends React.Component {
  componentDidMount() {
    // Update src to iframe
    // https://localhost:8000/  | basecamp.robolink.com/cwists/category
    
  }


  render() {
    return (
      <div className="content-panel content-1">
        <iframe id="iframeTutorials" src=""></iframe>
      </div>
    );
  }
}

export default ContentTutorials;
