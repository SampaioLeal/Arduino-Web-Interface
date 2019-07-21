<?php
class UpdateServo {
    
    protected $config;
    protected $cfgDir = "app/config/config.json";

    public function setPosition($pos) {
        $this->config = json_decode(file_get_contents($this->cfgDir));
        $this->config->servo = $pos;

        $newConfig = json_encode($this->config);
        file_put_contents($this->cfgDir, $newConfig);
    } 
}
