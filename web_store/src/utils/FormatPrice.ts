const FORMATER = new Intl.NumberFormat(undefined, {currency: "USD", style: "currency"});

export function formatPrice(price: number){
    return FORMATER.format(price);
}