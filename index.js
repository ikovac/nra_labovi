const customAddon = require('./build/Release/customaddon.node');

function getRandomNumber() {
    return Math.floor(Math.random() * 10000) + 1;
}

let arr = [];
for(let i = 0; i < 10000; i++) {
    arr.push(0);
}

function randomMemoryAccess() {
    let i = 0;
    let rand_index = 0;
    for(i = 0; i < 10000; i++) {
        rand_index = getRandomNumber();
        arr[rand_index] = rand_index;
    }
}

function sequentiallyMemoryAccess() {
    let i = 0;
    let rand_index = 0;
    for(i = 0; i < 10000; i++) {
        rand_index = getRandomNumber();
        arr[i] = rand_index;
    }
}

console.time("JS rand access");
randomMemoryAccess();
console.timeEnd("JS rand access");


console.time("JS sequentially access");
sequentiallyMemoryAccess();
console.timeEnd("JS sequentially access");


console.time("CPP rand access");
customAddon.randAccess();
console.timeEnd("CPP rand access");


console.time("CPP sequentially access");
customAddon.seqAccess();
console.timeEnd("CPP sequentially access");

