//
// Created by David Mike on 2020/2/27.
//

#include "MIMETypes.hpp"

void init(std::map<std::string, std::string>& obj)
{
    const char* MIMETypes = "3gp video/3gpp\n"
                            "aab application/x-authoware-bin\n"
                            "aam application/x-authoware-map\n"
                            "aas application/x-authoware-seg\n"
                            "ai application/postscript\n"
                            "aif audio/x-aiff\n"
                            "aifc audio/x-aiff\n"
                            "aiff audio/x-aiff\n"
                            "als audio/X-Alpha5\n"
                            "amc application/x-mpeg\n"
                            "ani application/octet-stream\n"
                            "apk application/vnd.android.package-archive\n"
                            "asc text/plain\n"
                            "asd application/astound\n"
                            "asf video/x-ms-asf\n"
                            "asn application/astound\n"
                            "asp application/x-asap\n"
                            "asx video/x-ms-asf\n"
                            "au audio/basic\n"
                            "avb application/octet-stream\n"
                            "avi video/x-msvideo\n"
                            "awb audio/amr-wb\n"
                            "bcpio application/x-bcpio\n"
                            "bin application/octet-stream\n"
                            "bld application/bld\n"
                            "bld2 application/bld2\n"
                            "bmp image/bmp\n"
                            "bpk application/octet-stream\n"
                            "bz2 application/x-bzip2\n"
                            "cal image/x-cals\n"
                            "ccn application/x-cnc\n"
                            "cco application/x-cocoa\n"
                            "cdf application/x-netcdf\n"
                            "cgi magnus-internal/cgi\n"
                            "chat application/x-chat\n"
                            "class application/octet-stream\n"
                            "clp application/x-msclip\n"
                            "cmx application/x-cmx\n"
                            "co application/x-cult3d-object\n"
                            "cod image/cis-cod\n"
                            "cpio application/x-cpio\n"
                            "cpt application/mac-compactpro\n"
                            "crd application/x-mscardfile\n"
                            "csh application/x-csh\n"
                            "csm chemical/x-csml\n"
                            "csml chemical/x-csml\n"
                            "css text/css\n"
                            "cur application/octet-stream\n"
                            "dcm x-lml/x-evm\n"
                            "dcr application/x-director\n"
                            "dcx image/x-dcx\n"
                            "dhtml text/html\n"
                            "dir application/x-director\n"
                            "dll application/octet-stream\n"
                            "dmg application/octet-stream\n"
                            "dms application/octet-stream\n"
                            "doc application/msword\n"
                            "dot application/x-dot\n"
                            "dvi application/x-dvi\n"
                            "dwf drawing/x-dwf\n"
                            "dwg application/x-autocad\n"
                            "dxf application/x-autocad\n"
                            "dxr application/x-director\n"
                            "ebk application/x-expandedbook\n"
                            "emb chemical/x-embl-dl-nucleotide\n"
                            "embl chemical/x-embl-dl-nucleotide\n"
                            "eps application/postscript\n"
                            "eri image/x-eri\n"
                            "es audio/echospeech\n"
                            "esl audio/echospeech\n"
                            "etc application/x-earthtime\n"
                            "etx text/x-setext\n"
                            "evm x-lml/x-evm\n"
                            "evy application/x-envoy\n"
                            "exe application/octet-stream\n"
                            "fh4 image/x-freehand\n"
                            "fh5 image/x-freehand\n"
                            "fhc image/x-freehand\n"
                            "fif image/fif\n"
                            "fm application/x-maker\n"
                            "fpx image/x-fpx\n"
                            "fvi video/isivideo\n"
                            "gau chemical/x-gaussian-input\n"
                            "gca application/x-gca-compressed\n"
                            "gdb x-lml/x-gdb\n"
                            "gif image/gif\n"
                            "gps application/x-gps\n"
                            "gtar application/x-gtar\n"
                            "gz application/x-gzip\n"
                            "hdf application/x-hdf\n"
                            "hdm text/x-hdml\n"
                            "hdml text/x-hdml\n"
                            "hlp application/winhlp\n"
                            "hqx application/mac-binhex40\n"
                            "htm text/html\n"
                            "html text/html\n"
                            "hts text/html\n"
                            "ice x-conference/x-cooltalk\n"
                            "ico application/octet-stream\n"
                            "ief image/ief\n"
                            "ifm image/gif\n"
                            "ifs image/ifs\n"
                            "imy audio/melody\n"
                            "ins application/x-NET-Install\n"
                            "ips application/x-ipscript\n"
                            "ipx application/x-ipix\n"
                            "it audio/x-mod\n"
                            "itz audio/x-mod\n"
                            "ivr i-world/i-vrml\n"
                            "j2k image/j2k\n"
                            "jad text/vnd.sun.j2me.app-descriptor\n"
                            "jam application/x-jam\n"
                            "jar application/java-archive\n"
                            "jnlp application/x-java-jnlp-file\n"
                            "jpe image/jpeg\n"
                            "jpeg image/jpeg\n"
                            "jpg image/jpeg\n"
                            "jpz image/jpeg\n"
                            "js application/x-javascript\n"
                            "jwc application/jwc\n"
                            "kjx application/x-kjx\n"
                            "lak x-lml/x-lak\n"
                            "latex application/x-latex\n"
                            "lcc application/fastman\n"
                            "lcl application/x-digitalloca\n"
                            "lcr application/x-digitalloca\n"
                            "lgh application/lgh\n"
                            "lha application/octet-stream\n"
                            "lml x-lml/x-lml\n"
                            "lmlpack x-lml/x-lmlpack\n"
                            "lsf video/x-ms-asf\n"
                            "lsx video/x-ms-asf\n"
                            "lzh application/x-lzh\n"
                            "m13 application/x-msmediaview\n"
                            "m14 application/x-msmediaview\n"
                            "m15 audio/x-mod\n"
                            "m3u audio/x-mpegurl\n"
                            "m3url audio/x-mpegurl\n"
                            "ma1 audio/ma1\n"
                            "ma2 audio/ma2\n"
                            "ma3 audio/ma3\n"
                            "ma5 audio/ma5\n"
                            "man application/x-troff-man\n"
                            "map magnus-internal/imagemap\n"
                            "mbd application/mbedlet\n"
                            "mct application/x-mascot\n"
                            "mdb application/x-msaccess\n"
                            "mdz audio/x-mod\n"
                            "me application/x-troff-me\n"
                            "mel text/x-vmel\n"
                            "mi application/x-mif\n"
                            "mid audio/midi\n"
                            "midi audio/midi\n"
                            "mif application/x-mif\n"
                            "mil image/x-cals\n"
                            "mio audio/x-mio\n"
                            "mmf application/x-skt-lbs\n"
                            "mng video/x-mng\n"
                            "mny application/x-msmoney\n"
                            "moc application/x-mocha\n"
                            "mocha application/x-mocha\n"
                            "mod audio/x-mod\n"
                            "mof application/x-yumekara\n"
                            "mol chemical/x-mdl-molfile\n"
                            "mop chemical/x-mopac-input\n"
                            "mov video/quicktime\n"
                            "movie video/x-sgi-movie\n"
                            "mp2 audio/x-mpeg\n"
                            "mp3 audio/x-mpeg\n"
                            "mp4 video/mp4\n"
                            "mpc application/vnd.mpohun.certificate\n"
                            "mpe video/mpeg\n"
                            "mpeg video/mpeg\n"
                            "mpg video/mpeg\n"
                            "mpg4 video/mp4\n"
                            "mpga audio/mpeg\n"
                            "mpn application/vnd.mophun.application\n"
                            "mpp application/vnd.ms-project\n"
                            "mps application/x-mapserver\n"
                            "mrl text/x-mrml\n"
                            "mrm application/x-mrm\n"
                            "ms application/x-troff-ms\n"
                            "mts application/metastream\n"
                            "mtx application/metastream\n"
                            "mtz application/metastream\n"
                            "mzv application/metastream\n"
                            "nar application/zip\n"
                            "nbmp image/nbmp\n"
                            "nc application/x-netcdf\n"
                            "ndb x-lml/x-ndb\n"
                            "ndwn application/ndwn\n"
                            "nif application/x-nif\n"
                            "nmz application/x-scream\n"
                            "nokia-op-logo image/vnd.nok-oplogo-color\n"
                            "npx application/x-netfpx\n"
                            "nsnd audio/nsnd\n"
                            "nva application/x-neva1\n"
                            "oda application/oda\n"
                            "oom application/x-AtlasMate-Plugin\n"
                            "pac audio/x-pac\n"
                            "pae audio/x-epac\n"
                            "pan application/x-pan\n"
                            "pbm image/x-portable-bitmap\n"
                            "pcx image/x-pcx\n"
                            "pda image/x-pda\n"
                            "pdb chemical/x-pdb\n"
                            "pdf application/pdf\n"
                            "pfr application/font-tdpfr\n"
                            "pgm image/x-portable-graymap\n"
                            "pict image/x-pict\n"
                            "pm application/x-perl\n"
                            "pmd application/x-pmd\n"
                            "png image/png\n"
                            "pnm image/x-portable-anymap\n"
                            "pnz image/png\n"
                            "pot application/vnd.ms-powerpoint\n"
                            "ppm image/x-portable-pixmap\n"
                            "pps application/vnd.ms-powerpoint\n"
                            "ppt application/vnd.ms-powerpoint\n"
                            "pqf application/x-cprplayer\n"
                            "pqi application/cprplayer\n"
                            "prc application/x-prc\n"
                            "proxy application/x-ns-proxy-autoconfig\n"
                            "ps application/postscript\n"
                            "ptlk application/listenup\n"
                            "pub application/x-mspublisher\n"
                            "pvx video/x-pv-pvx\n"
                            "qcp audio/vnd.qcelp\n"
                            "qt video/quicktime\n"
                            "qti image/x-quicktime\n"
                            "qtif image/x-quicktime\n"
                            "r3t text/vnd.rn-realtext3d\n"
                            "ra audio/x-pn-realaudio\n"
                            "ram audio/x-pn-realaudio\n"
                            "rar application/x-rar-compressed\n"
                            "ras image/x-cmu-raster\n"
                            "rdf application/rdf+xml\n"
                            "rf image/vnd.rn-realflash\n"
                            "rgb image/x-rgb\n"
                            "rlf application/x-richlink\n"
                            "rm audio/x-pn-realaudio\n"
                            "rmf audio/x-rmf\n"
                            "rmm audio/x-pn-realaudio\n"
                            "rmvb audio/x-pn-realaudio\n"
                            "rnx application/vnd.rn-realplayer\n"
                            "roff application/x-troff\n"
                            "rp image/vnd.rn-realpix\n"
                            "rpm audio/x-pn-realaudio-plugin\n"
                            "rt text/vnd.rn-realtext\n"
                            "rte x-lml/x-gps\n"
                            "rtf application/rtf\n"
                            "rtg application/metastream\n"
                            "rtx text/richtext\n"
                            "rv video/vnd.rn-realvideo\n"
                            "rwc application/x-rogerwilco\n"
                            "s3m audio/x-mod\n"
                            "s3z audio/x-mod\n"
                            "sca application/x-supercard\n"
                            "scd application/x-msschedule\n"
                            "sdf application/e-score\n"
                            "sea application/x-stuffit\n"
                            "sgm text/x-sgml\n"
                            "sgml text/x-sgml\n"
                            "sh application/x-sh\n"
                            "shar application/x-shar\n"
                            "shtml magnus-internal/parsed-html\n"
                            "shw application/presentations\n"
                            "si6 image/si6\n"
                            "si7 image/vnd.stiwap.sis\n"
                            "si9 image/vnd.lgtwap.sis\n"
                            "sis application/vnd.symbian.install\n"
                            "sit application/x-stuffit\n"
                            "skd application/x-Koan\n"
                            "skm application/x-Koan\n"
                            "skp application/x-Koan\n"
                            "skt application/x-Koan\n"
                            "slc application/x-salsa\n"
                            "smd audio/x-smd\n"
                            "smi application/smil\n"
                            "smil application/smil\n"
                            "smp application/studiom\n"
                            "smz audio/x-smd\n"
                            "snd audio/basic\n"
                            "spc text/x-speech\n"
                            "spl application/futuresplash\n"
                            "spr application/x-sprite\n"
                            "sprite application/x-sprite\n"
                            "spt application/x-spt\n"
                            "src application/x-wais-source\n"
                            "stk application/hyperstudio\n"
                            "stm audio/x-mod\n"
                            "sv4cpio application/x-sv4cpio\n"
                            "sv4crc application/x-sv4crc\n"
                            "svf image/vnd\n"
                            "svg image/svg-xml\n"
                            "svh image/svh\n"
                            "svr x-world/x-svr\n"
                            "swf application/x-shockwave-flash\n"
                            "swfl application/x-shockwave-flash\n"
                            "t application/x-troff\n"
                            "tad application/octet-stream\n"
                            "talk text/x-speech\n"
                            "tar application/x-tar\n"
                            "taz application/x-tar\n"
                            "tbp application/x-timbuktu\n"
                            "tbt application/x-timbuktu\n"
                            "tcl application/x-tcl\n"
                            "tex application/x-tex\n"
                            "texi application/x-texinfo\n"
                            "texinfo application/x-texinfo\n"
                            "tgz application/x-tar\n"
                            "thm application/vnd.eri.thm\n"
                            "tif image/tiff\n"
                            "tiff image/tiff\n"
                            "tki application/x-tkined\n"
                            "tkined application/x-tkined\n"
                            "toc application/toc\n"
                            "toy image/toy\n"
                            "tr application/x-troff\n"
                            "trk x-lml/x-gps\n"
                            "trm application/x-msterminal\n"
                            "tsi audio/tsplayer\n"
                            "tsp application/dsptype\n"
                            "tsv text/tab-separated-values\n"
                            "tsv text/tab-separated-values\n"
                            "ttf application/octet-stream\n"
                            "ttz application/t-time\n"
                            "txt text/plain\n"
                            "ult audio/x-mod\n"
                            "ustar application/x-ustar\n"
                            "uu application/x-uuencode\n"
                            "uue application/x-uuencode\n"
                            "vcd application/x-cdlink\n"
                            "vcf text/x-vcard\n"
                            "vdo video/vdo\n"
                            "vib audio/vib\n"
                            "viv video/vivo\n"
                            "vivo video/vivo\n"
                            "vmd application/vocaltec-media-desc\n"
                            "vmf application/vocaltec-media-file\n"
                            "vmi application/x-dreamcast-vms-info\n"
                            "vms application/x-dreamcast-vms\n"
                            "vox audio/voxware\n"
                            "vqe audio/x-twinvq-plugin\n"
                            "vqf audio/x-twinvq\n"
                            "vql audio/x-twinvq\n"
                            "vre x-world/x-vream\n"
                            "vrml x-world/x-vrml\n"
                            "vrt x-world/x-vrt\n"
                            "vrw x-world/x-vream\n"
                            "vts workbook/formulaone\n"
                            "wav audio/x-wav\n"
                            "wax audio/x-ms-wax\n"
                            "wbmp image/vnd.wap.wbmp\n"
                            "web application/vnd.xara\n"
                            "wi image/wavelet\n"
                            "wis application/x-InstallShield\n"
                            "wm video/x-ms-wm\n"
                            "wma audio/x-ms-wma\n"
                            "wmd application/x-ms-wmd\n"
                            "wmf application/x-msmetafile\n"
                            "wml text/vnd.wap.wml\n"
                            "wmlc application/vnd.wap.wmlc\n"
                            "wmls text/vnd.wap.wmlscript\n"
                            "wmlsc application/vnd.wap.wmlscriptc\n"
                            "wmlscript text/vnd.wap.wmlscript\n"
                            "wmv audio/x-ms-wmv\n"
                            "wmx video/x-ms-wmx\n"
                            "wmz application/x-ms-wmz\n"
                            "wpng image/x-up-wpng\n"
                            "wpt x-lml/x-gps\n"
                            "wri application/x-mswrite\n"
                            "wrl x-world/x-vrml\n"
                            "wrz x-world/x-vrml\n"
                            "ws text/vnd.wap.wmlscript\n"
                            "wsc application/vnd.wap.wmlscriptc\n"
                            "wv video/wavelet\n"
                            "wvx video/x-ms-wvx\n"
                            "wxl application/x-wxl\n"
                            "x-gzip application/x-gzip\n"
                            "xar application/vnd.xara\n"
                            "xbm image/x-xbitmap\n"
                            "xdm application/x-xdma\n"
                            "xdma application/x-xdma\n"
                            "xdw application/vnd.fujixerox.docuworks\n"
                            "xht application/xhtml+xml\n"
                            "xhtm application/xhtml+xml\n"
                            "xhtml application/xhtml+xml\n"
                            "xla application/vnd.ms-excel\n"
                            "xlc application/vnd.ms-excel\n"
                            "xll application/x-excel\n"
                            "xlm application/vnd.ms-excel\n"
                            "xls application/vnd.ms-excel\n"
                            "xlt application/vnd.ms-excel\n"
                            "xlw application/vnd.ms-excel\n"
                            "xm audio/x-mod\n"
                            "xml text/xml\n"
                            "xmz audio/x-mod\n"
                            "xpi application/x-xpinstall\n"
                            "xpm image/x-xpixmap\n"
                            "xsit text/xml\n"
                            "xsl text/xml\n"
                            "xul text/xul\n"
                            "xwd image/x-xwindowdump\n"
                            "xyz chemical/x-pdb\n"
                            "yz1 application/x-yz1\n"
                            "z application/x-compress\n"
                            "zac application/x-zaurus-zac\n"
                            "zip application/zip";

    std::istringstream is(MIMETypes);
    std::string key, value;
    while (is >> key >> value)
    {
        obj[key] = value;
    }
    obj[""] = "application/octet-stream";
}

const std::map<std::string, std::string>& greatbridf::Static::mimeTypes()
{
    static bool first = false;
    static std::map<std::string, std::string> obj;
    if (!first)
    {
        ::init(obj);
        first = true;
    }
    return obj;
}