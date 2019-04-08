const customAddon = require('./build/Release/customaddon.node');

function getRandomNumber() {
    return Math.floor(Math.random() * 5) + 1;
}

const arr_length = 200000;

let sum = 0;
console.time("JS sum");
for(let i = 0; i < arr_length; i ++) {
    sum += getRandomNumber();
}
console.timeEnd("JS sum");

console.time("CPP sum");
customAddon.sum();
console.timeEnd("CPP sum");


console.time("CPP paralel sum");
customAddon.sumParalel();
console.timeEnd("CPP paralel sum");


// Komentar na čudan rezultat
// https://stackoverflow.com/questions/17348228/code-runs-6-times-slower-with-2-threads-than-with-1


