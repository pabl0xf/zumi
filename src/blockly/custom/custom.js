
$( document ).ready(function() {

    var searchParams = new URLSearchParams(location.search);
    if(searchParams.has('ek')){
        var encodedParam = searchParams.get('ek');
        var codePlainText = decodeURIComponent(escape(window.atob(encodedParam)));
        setTimeout(function(){
             var cell = Jupyter.notebook.get_cell(0);
             cell.set_text(codePlainText); 
            }.bind(this), 1500);
        
    }
});
