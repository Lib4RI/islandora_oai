<?php

function build_citation($content, $style){
    module_load_include('module', 'citeproc', 'citeproc');
    $s = citeproc_style($style);
    if ($s){
        $citation = citeproc_bibliography_from_mods($s, $content);
        $citation = str_replace('<div class="csl-bib-body"><div class="csl-entry">', '', $citation);
        $citation = str_replace('</div></div>', '', $citation);
        $citation = str_replace('&', '&amp;', $citation);
        $content = str_replace("</mods>", "<citation>$citation</citation></mods>", $content);
    }
    return $content;
}