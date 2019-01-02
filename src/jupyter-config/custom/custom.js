
console.log("Loading autosave disable script");
require(['base/js/namespace', 'base/js/events'], function (Jupyter, events) {
  Jupyter.notebook.set_autosave_interval(0);
});
window.addEventListener('message', function(event) { 
    if (~event.origin.indexOf('http')) { 
        // The data has been sent from your site 
         if(event && event.data){
         }
        // The data sent with postMessage is stored in event.data 
               if(Jupyter){
                 var runCommands = false;
                 var commands = null

                 if(event.data.search('RESTART=TRUE') !== -1){
                   Jupyter.notebook.clear_all_output(); 
                   Jupyter.notebook.restart_kernel({confirm:false});
                   return false;
                 }

                 if(event.data.search('STOP=TRUE') !== -1){
                   $('#run_int button')[1].click();
                   return false;
                 }

                 if(event.data.search('RUN=TRUE') !== -1){
                   runCommands = true; 
                   commands  = event.data.substr(0, event.data.length-8)          
                 }

                 else {
                   commands = event.data;
                 }
                     
                 var codePlainText = decodeURIComponent(escape(window.atob(commands)));
                 var cell = Jupyter.notebook.get_cell(0);
                 cell.set_text(codePlainText);
                 if(runCommands){
                   cell.notebook.execute_cell();
                 }
                 console.log(Jupyter);
              }
 
          console.log(event.data); 
    } 
    // IMPORTANT: Check the origin of the data! 
        // The data has been sent from your site 
        // The data sent with postMessage is stored in event.data 
        console.log(event.data); 
}); 
window.onbeforeunload = null;
   jQuery('<div/>', {
    id: 'spinner',
    class: 'loader',
    title: 'now this div has a title!'
}).appendTo('html');

$( document ).ready(function() {
    var searchParams = new URLSearchParams(location.search);
    setTimeout(function(){
 
    var out = searchParams.has('out');
    if(out){
               document.getElementById('maintoolbar').style.display = "none";
               document.getElementById('maintoolbar-container').style.display = "none";
               document.getElementsByClassName('input')[0].style.position = "absolute";
               document.getElementsByClassName('input')[0].style.width = "100%";
               document.getElementsByClassName('input')[0].style.height = "0px";
               document.getElementsByClassName('input')[0].style.top = "-30px";

                Jupyter.notebook.set_autosave_interval(0);

             }
        else {
             //document.getElementById('site').style = "height: 100% !important";  
        }
       document.body.style.visibility = 'visible'; 
       $('#spinner').hide();
            }.bind(this), 2000);

    if(searchParams.has('src')){
        var encodedParam = searchParams.get('src');
        var run = searchParams.has('run');
        var out = searchParams.has('out');
        var codePlainText = decodeURIComponent(escape(window.atob(encodedParam)));
        setTimeout(function(){
             var cell = Jupyter.notebook.get_cell(0);
             cell.set_text(codePlainText);
             if(out){
               document.getElementById('maintoolbar').style.display = "none";
               document.getElementById('maintoolbar-container').style.display = "none";
               document.getElementsByClassName('input')[0].style.display = "none";
             }
             document.body.style.visibility = 'visible';
             if(run){
                 cell.notebook.execute_cell();
             }
             $('#spinner').hide(); 
            }.bind(this), 2000);
        
    }
});
