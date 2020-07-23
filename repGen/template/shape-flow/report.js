var basePath;
var wheelAccumulator=0;
function shapeName()
{
    let r=document.getElementsByClassName("row")[0];
    let l=r.children.length;
    for(let i=0;i<l;i++)
    {
        let c=r.children[i];
        let buttons=c.children[0].children;
        for(let j=0;j<buttons.length;j++)
        {
            if(buttons[j].classList.contains("selected"))
            {
                if( buttons[j].getAttribute("type")==="shape" )
                {
                    return buttons[j].getAttribute("path");
                }
            }
        }
    }
}
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
function loadFigure()
{
    let relPath=buildPath();
    let fullPath=basePath.concat("/",relPath,"summary.svg");
    let summary_flow = getActiveSubdisplay("summary-flow");
    summary_flow.children[0].setAttribute("src",fullPath);
    let odrModel = getActiveSubdisplay("odr-model");
    let odrImagePath = fullPath.substr(0,fullPath.lastIndexOf("/"));
    odrImagePath=odrImagePath.concat("/","odr.svg");
    odrModel.children[0].setAttribute("src",odrImagePath);
    restartImageSequence();
    console.log(odrImagePath);
}
function select(el)
{
    _select(el,true);
}
function _select(el,load_flag)
{
    let list_li=el.parentElement.children;
    for (let i=0;i<list_li.length;i++)
    {
        if(list_li[i].hasAttribute("type"))
        {
            list_li[i].className="button";
        }
    }
    el.className="button selected";
    if(load_flag)
    {
        loadFigure();
    }
}
function default_buttons()
{
    let r=document.getElementsByClassName("row")[0];
    let l=r.children.length-1;
    for(let i=0;i<l;i++)
    {
        let c=r.children[i];
        if(c.hasAttribute("menu"))
        {
            let buttons = c.children[0].children;
            let first = buttons[1];
            _select(first, true);
        }
    }
}
function freeze(el)
{
    let display = document.getElementsByClassName("display")[0];
    if(el.innerHTML==="Freeze")
    {
        el.innerHTML="Unfreeze";
        for(let i=0;i<display.children.length;i++)
        {
            display.children[i].classList.remove("full");
            display.children[i].classList.remove("hidden");
            display.children[i].classList.remove("active");
            display.children[i].classList.add("half");
        }
        display.children[1].classList.add("active");
        loadFigure();
    }else
    {
        el.innerHTML="Freeze";
        for(let i=0;i<display.children.length;i++)
        {
            display.children[i].classList.remove("half");
        }
        display.children[0].classList.add("full");
        display.children[0].classList.add("active");
        display.children[1].classList.add("hidden");
        loadFigure();
    }
}
function toogleDisplay(class_to_display,class_to_hidden)
{
    let display = getCurrentDisplay();
    for(let i=0;i<display.children.length;++i)
    {
        if(display.children[i].classList.contains(class_to_hidden))
        {
            display.children[i].classList.add("hidden");
        }else if(display.children[i].classList.contains(class_to_display))
        {
            display.children[i].classList.remove("hidden");
        }
    }
}
function restartImageSequence()
{
    let display = getCurrentDisplay();
    for(let i=0;i<display.children.length;++i)
    {
        if(display.children[i].classList.contains("image-sequence"))
        {
            display.children[i].setAttribute("img_seq","0");
        }
    }
    let imageName = imageName("1");
    let relPath = buildPath();
    let imagePath = basePath.concat("/",relPath,imageName);
    let subdisplay = getActiveSubdisplay("image-sequence");
    subdisplay.children[0].setAttribute("src",imagePath);
}
function summary(el)
{
    if(el.innerHTML==="Summary")
    {
        el.innerHTML="Image Sequence";
        toogleDisplay("summary-flow","image-sequence");
    }else
    {
        el.innerHTML="Summary";
        toogleDisplay("image-sequence","summary-flow");
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

    default_buttons();
    document.body.style.visibility="visible";
    for(let i=0;i<document.getElementsByClassName("image-sequence").length;++i)
    {
        let el = document.getElementsByClassName("image-sequence")[i];
        el.addEventListener("wheel",function(event){wheelEvent(el,event);});
    }
}
function imageName(imgSeq)
{
    let name="";
    for(let i=4-imgSeq.length;i>0;--i)
    {
        name+="0";
    }
    name+=imgSeq;
    name+=".png";
    return name;
}
function wheelEvent(el,event)
{
    event.preventDefault();
    wheelAccumulator+=event.deltaY;
    let subdisplay = getActiveSubdisplay("image-sequence");
    let imgEl = subdisplay.children[0];
    let imgSeq = imgEl.getAttribute("img_seq");
    let imageName = imageName(imgSeq);
    let relPath = buildPath();
    let imagePath = basePath.concat("/",relPath,imageName);
    imgEl.setAttribute("src",imagePath);
    if(wheelAccumulator < -5)
    {
        imgEl.setAttribute("img_seq", (parseInt(imgSeq) + 1).toString());
        wheelAccumulator=0;
    }
    else if(wheelAccumulator > 5)
    {
        imgEl.setAttribute("img_seq",(parseInt(imgSeq)-1).toString());
        wheelAccumulator=0;
    }
}
window.onload=init;