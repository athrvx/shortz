const result = document.getElementById("result");
const link = document.getElementById("shortLink");
const button = document.getElementById("shortenBtn");
const toast = document.getElementById("toast");

async function shortenUrl() {

    const url = document.getElementById("url").value.trim();
    const alias = document.getElementById("alias").value.trim();

    result.className = "hidden";

    if(url === ""){
        result.className = "error";
        result.textContent = "Please enter a URL.";
        return;
    }

    button.disabled = true;
    button.textContent = "Shortening...";

    try{

        const response = await fetch(
            "http://localhost:8080/shorten",
            {
                method:"POST",

                headers:{
                    "Content-Type":"application/json"
                },

                body:JSON.stringify({
                    url:url,
                    customAlias:alias
                })
            });

        const data = await response.json();

        if(data.success){

            link.href = data.shortUrl;
            link.textContent = data.shortUrl;

            result.className = "";
            result.classList.remove("hidden");

        }else{

            result.className = "error";
            result.textContent = data.error;
        }

    }catch(e){

        result.className = "error";
        result.textContent = "Unable to connect to backend.";

    }finally{

        button.disabled = false;
        button.textContent = "Shorten URL";
    }
}

document.getElementById("copyBtn").addEventListener("click", async ()=>{

    await navigator.clipboard.writeText(link.href);

    toast.classList.remove("hidden");
    toast.classList.add("show");

    setTimeout(()=>{
        toast.classList.remove("show");
        toast.classList.add("hidden");
    },2000);

});

document.getElementById("url").addEventListener("keydown",(e)=>{

    if(e.key==="Enter")
        shortenUrl();

});

document.getElementById("alias").addEventListener("keydown",(e)=>{

    if(e.key==="Enter")
        shortenUrl();

});