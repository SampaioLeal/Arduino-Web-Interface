<?php

//Chama as classes
spl_autoload_register(function ($class_name) {
    include ("app/controllers/" . $class_name . '.php');
});

//Define as classes
$updateDisplay = new UpdateDisplay();
$updateServo = new UpdateServo();

//Atualizar Display LCD
if(isset($_POST['display'])) {
    $line1 = $_POST['line1'];
    $line2 = $_POST['line2'];
    $updateDisplay->setDisplay($line1, $line2);
}

//Atualizar ServoMotor
if(isset($_POST['servo'])) {
    $updateServo->setPosition($_POST['servo']);
}