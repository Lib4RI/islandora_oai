<?php

function build_citation($content, $style_s){
    
    if ($style_s){
        module_load_include('module', 'citeproc', 'citeproc');
        
        if ($style_s == 1){
            $style_a = CSL::GetNames();
        }
        else {
            $style_a = explode(':', $style_s);
        }
        
        $st = [];
        foreach ($style_a as $style){
            $s = citeproc_style($style);
            if($s && (strtolower($style) != 'bibtex')){
                array_push($st, $s);
            }
        }
        
        $edited = false;
        $citations = '';
        foreach ($st as $cstyle){
            $citation = citeproc_bibliography_from_mods($cstyle, $content);
            $citation = str_replace('<div class="csl-bib-body"><div class="csl-entry">', '', $citation);
            $citation = str_replace('</div></div>', '', $citation);
            $citation = str_replace('&', '&amp;', $citation);
            $citation = str_replace('<', '&lt;', $citation);
            $citation = str_replace('>', '&gt;', $citation);
//            $citation = str_replace('"', '&quot;', $citation);
//            $citation = str_replace("'", '&apos;', $citation);
//            $citation = "<$cstyle[name]><![CDATA[$citation]]></$cstyle[name]>";
            $citation = "<$cstyle[name]>$citation</$cstyle[name]>";
            $citations .= $citation;
            $edited = true;
        }
        if ($edited)
            $content = str_replace("</mods>", 
"  <extension>
    <bibliographicCitation>
      $citations
    </bibliographicCitation>
  </extension>
</mods>", $content);
    }
    
    return $content;
}