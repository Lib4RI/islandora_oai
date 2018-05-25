<?php

function build_citation($content, $style){
    return str_replace("</mods>", "<addInfo>aaa</addInfo></mods>", $content);
}