function maxMoneyLeft (credLim, gifts) {
    const resultarr = [];
    for (let index = 1; index <= credLim; index++) {
        let credit = index;
        for(let gift of gifts) {
            if(credit >= gift) {
                credit -= gift;
            } 
        }
        resultarr.push(credit);
    }
    return Math.max(...resultarr);
}

const credLim = 10;
const gifts = [5,4,1];
const n = 3;
