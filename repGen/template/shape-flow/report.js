var basePath;
var wheel_accumulator=0;
function shape_name()
{
    var r=document.getElementsByClassName("row")[0];
    var l=r.children.length;
    for(var i=0;i<l;i++)
    {
        var c=r.children[i];
        var buttons=c.children[0].children;
        for(var j=0;j<buttons.length;j++)
        {
            if(buttons[j].classList.contains("selected"))
            {
                if( buttons[j].getAttribute("type")=="shape" )
                {
                    return buttons[j].getAttribute("path");
                }
            }
        }
    }
}
function build_path()
{
    var r=document.getElementsByClassName("row")[0];
    var l=r.children.length;
    var relPath="";
    for(var i=0;i<l;i++)
    {
        var c=r.children[i];
        var buttons=c.children[0].children;
        for(var j=0;j<buttons.length;j++)
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
function get_current_display()
{
    var display = document.getElementsByClassName("display")[0];
    for(var i=0;i<display.children.length;++i)
    {
        if(display.children[i].classList.contains("active"))
        {
            return display.children[i];
        }
    }
}
function get_active_subdisplay(display_class)
{
    var activeDisplay = get_current_display();
    var subdisplays = activeDisplay.children;
    for(var i=0;i<subdisplays.length;++i)
    {
        if(subdisplays[i].classList.contains(display_class))
        {
            return subdisplays[i];
        }
    }
}
function load_figure()
{
    var relPath=build_path();
    var shapeName = shape_name();
    var fullPath=basePath.concat("/",relPath,"summary.svg");
    var summary_flow = get_active_subdisplay("summary-flow");
    summary_flow.children[0].setAttribute("src",fullPath);
    var odr_model = get_active_subdisplay("odr-model");
    var odr_image_path = fullPath.substr(0,fullPath.lastIndexOf("/"));
    odr_image_path=odr_image_path.concat("/","odr.svg");
    odr_model.children[0].setAttribute("src",odr_image_path);
    restart_image_sequence();
    console.log(odr_image_path);
}
function select(el)
{
    _select(el,true);
}
function _select(el,load_flag)
{
    var list_li=el.parentElement.children;
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
function default_buttons()
{
    var r=document.getElementsByClassName("row")[0];
    var l=r.children.length-1;
    for(var i=0;i<l;i++)
    {
        var c=r.children[i];
        if(c.hasAttribute("menu"))
        {
            var buttons = c.children[0].children;
            var first = buttons[1];
            _select(first, true);
        }
    }
}
function freeze(el)
{
    var display = document.getElementsByClassName("display")[0];
    if(el.innerHTML=="Freeze")
    {
        el.innerHTML="Unfreeze";
        for(var i=0;i<display.children.length;i++)
        {
            display.children[i].classList.remove("full");
            display.children[i].classList.remove("hidden");
            display.children[i].classList.remove("active");
            display.children[i].classList.add("half");
        }
        display.children[1].classList.add("active");
        load_figure();
    }else
    {
        el.innerHTML="Freeze";
        for(var i=0;i<display.children.length;i++)
        {
            display.children[i].classList.remove("half");
        }
        display.children[0].classList.add("full");
        display.children[0].classList.add("active");
        display.children[1].classList.add("hidden");
        load_figure();
    }
}
function toogle_display(class_to_display,class_to_hidden)
{
    var display = get_current_display();
    for(var i=0;i<display.children.length;++i)
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
function restart_image_sequence()
{
    var display = get_current_display();
    for(var i=0;i<display.children.length;++i)
    {
        if(display.children[i].classList.contains("image-sequence"))
        {
            display.children[i].setAttribute("img_seq","0");
        }
    }
    var imageName = image_name("1");
    var relPath = build_path();
    var imagePath = basePath.concat("/",relPath,imageName);
    var subdisplay = get_active_subdisplay("image-sequence");
    subdisplay.children[0].setAttribute("src",imagePath);
}
function summary(el)
{
    if(el.innerHTML=="Summary")
    {
        el.innerHTML="Image Sequence";
        toogle_display("summary-flow","image-sequence");
    }else
    {
        el.innerHTML="Summary";
        toogle_display("image-sequence","summary-flow");
    }
}
function open_src(el)
{
    document.location.href=el.getAttribute("src");
}
function init()
{
    basePath=window.prompt("Enter images base folder");
    if(basePath=="")
    {
        basePath=window.location.toString();
        basePath=basePath.substring(0, basePath.lastIndexOf("/") );
    }else{
        basePath="file://".concat(basePath);
    }
    default_buttons();
    document.body.style.visibility="visible";
    for(var i=0;i<document.getElementsByClassName("image-sequence").length;++i)
    {
        var el = document.getElementsByClassName("image-sequence")[i];
        el.addEventListener("wheel",function(event){wheel_event(el,event);});
    }
}
function image_name(imgSeq)
{
    var name="";
    for(var i=4-imgSeq.length;i>0;--i)
    {
        name+="0";
    }
    name+=imgSeq;
    name+=".png";
    return name;
}
function wheel_event(el,event)
{
    event.preventDefault();
    wheel_accumulator+=event.deltaY;
    var subdisplay = get_active_subdisplay("image-sequence");
    var imgEl = subdisplay.children[0];
    var imgSeq = imgEl.getAttribute("img_seq");
    var imageName = image_name(imgSeq);
    var relPath = build_path();
    var imagePath = basePath.concat("/",relPath,imageName);
    imgEl.setAttribute("src",imagePath);
    if(wheel_accumulator < -5)
    {
        imgEl.setAttribute("img_seq", (parseInt(imgSeq) + 1).toString());
        wheel_accumulator=0;
    }
    else if(wheel_accumulator > 5)
    {
        imgEl.setAttribute("img_seq",(parseInt(imgSeq)-1).toString());
        wheel_accumulator=0;
    }
}
window.onload=init;