<?php

function build_citation($content, $style){
    module_load_include('module', 'citeproc', 'citeproc');
    $s = citeproc_style($style);
    $citation = citeproc_bibliography_from_mods($s, $content);
    $citation = str_replace('<div class="csl-bib-body"><div class="csl-entry">', '', $citation);
    $citation = str_replace('</div></div>', '', $citation);
    $citation = str_replace('&', '&amp;', $citation);
    return str_replace("</mods>", "<citation>$citation</citation></mods>", $content);
}