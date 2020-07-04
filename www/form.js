const button = document.getElementById("sendButton")
const name = document.getElementById("iName")
const phone = document.getElementById("iPhone")

button.addEventListener("click", function(e){
    e.preventDefault()
    console.log(name.value, phone.value)

    const xhr = new XMLHttpRequest();
    xhr.open('POST', 'http://httpbin.org/anything');
    xhr.setRequestHeader("Content-Type", "application/json;charset=UTF-8");
    xhr.send(JSON.stringify({name: name.value, phone: phone.value}));

})