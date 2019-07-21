$(document).ready(function () {

    //Preparando a página
    $.post("app/config/config.json", function(data) {
        var config = $.parseJSON(JSON.stringify(data));
        $("#line1").val(config.display.line1);
        $("#line2").val(config.display.line2);
    });

    //Declaração de Funções
    function updateLCD(linha1, linha2) {
        $.post("request.php", { display: true, line1: linha1, line2: linha2 });
    }
    function updateServo(pos) {
        $.post("request.php", { servo: pos });
    }

    //Definir o texto do DisplayLCD ao digitar
    $(document).on("keyup", ".line", function(e){
        updateLCD($("#line1").val(), $("#line2").val());
    });

    //Initialize RangeSlider JS
    $("#servo").rangeslider({
        polyfill: false,
        onSlide: function(position, value) {
            updateServo(value);
        },
        onSlideEnd: function(position, value){
            updateServo(value);
        }
    });
    
});
