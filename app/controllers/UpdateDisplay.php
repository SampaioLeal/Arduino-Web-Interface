<?php
class UpdateDisplay {
    
    protected $config;
    protected $cfgDir = "app/config/config.json";

    public function setDisplay($line1, $line2) {
        $this->config = json_decode(file_get_contents($this->cfgDir));
        $display = $this->config->display;

        $display->line1 = $line1;
        $display->line2 = $line2;

        $newConfig = json_encode($this->config);
        file_put_contents($this->cfgDir, $newConfig);
    } 
}
