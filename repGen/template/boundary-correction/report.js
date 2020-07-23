var basePath;

function buildPath()
{
    let r=document.getElementsByClassName("row")[0];
    let l=r.children.length;
    let relPath="";
    for(let i=0;i<l;i++)
    {
        let c=r.children[i];
        let buttons=c.children[0].children;
        for(let j=0;j<buttons.length;j++)
        {
            if(buttons[j].classList.contains("selected"))
            {
                if( buttons[j].hasAttribute("path") )
                {
                    relPath = relPath.concat(buttons[j].getAttribute("path"), "/");
                }
            }
        }
    }

    return relPath;
}

function getCurrentDisplay()
{
    let display = document.getElementsByClassName("display")[0];
    for(let i=0;i<display.children.length;++i)
    {
        if(display.children[i].classList.contains("active"))
        {
            return display.children[i];
        }
    }
}

function getActiveSubdisplay(display_class)
{
    let activeDisplay = getCurrentDisplay();
    let subdisplays = activeDisplay.children;
    for(let i=0;i<subdisplays.length;++i)
    {
        if(subdisplays[i].classList.contains(display_class))
        {
            return subdisplays[i];
        }
    }
}

function load_figure()
{
    let relPath=buildPath();

    let seedMasks_img=basePath.concat("/",relPath,"seeds.png");
    let seedMasks = getActiveSubdisplay("seeds");
    seedMasks.children[0].setAttribute("src",seedMasks_img);

    let grabcutSegImg = basePath.concat("/",relPath,"gc-seg.png");
    let grabcutSeg = getActiveSubdisplay("grabcut-seg");
    grabcutSeg.children[0].setAttribute("src",grabcutSegImg);

    let corrected_seg_img = basePath.concat("/",relPath,"corrected-seg.png");
    let corrected_seg = getActiveSubdisplay("corrected-seg");
    corrected_seg.children[0].setAttribute("src",corrected_seg_img);
}


function select(el)
{
    _select(el,true);
}

function _select(el,load_flag)
{
    let list_li=el.parentElement.children;
    for (var i=0;i<list_li.length;i++)
    {
        if(list_li[i].hasAttribute("type"))
        {
            list_li[i].className="button";
        }

    }
    el.className="button selected";
    if(load_flag)
    {
        load_figure();
    }

}

function defaultButtons()
{
    let r=document.getElementsByClassName("row")[0];
    let l=r.children.length;
    for(var i=0;i<l;i++)
    {
        let c=r.children[i];
        if(c.hasAttribute("menu"))
        {
            var buttons = c.children[0].children;
            var first = buttons[1];
            _select(first, true);
        }
    }
}

function openSrc(el)
{
    document.location.href=el.getAttribute("src");
}

function init()
{
    basePath=window.location.toString();
    basePath=basePath.substring(0, basePath.lastIndexOf("/") );

    defaultButtons();
    load_figure();
    document.body.style.visibility="visible";

}


window.onload=init;