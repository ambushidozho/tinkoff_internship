function isRightLetters (str) {
   
    checkword = 'TINKOFF';

    if(str.length !== checkword.length) {
        return false;
    }

    for(let sym of checkword) {
        const index = str.indexOf(sym);
        if(index !== -1) {
            str = str.slice(0, index) + str.slice(index + 1);
        } else {
            return false;
        }
    }
    return true;
}

const str = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ';

isRightLetters(str) ? console.log('YES') : console.log('NO');
isRightLetters('FFOKNIT') ? console.log('YES') : console.log('NO');
isRightLetters('TINKOFFF') ? console.log('YES') : console.log('NO');
isRightLetters('AAAA') ? console.log('YES') : console.log('NO');
isRightLetters('TINKOFF') ? console.log('YES') : console.log('NO');
