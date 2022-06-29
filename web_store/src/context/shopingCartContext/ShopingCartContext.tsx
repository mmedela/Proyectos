import { createContext, ReactNode, useContext, useState } from "react";
import { ShoppingCart } from "../../components/shoppingCart/ShoppingCart";
import { useLocalStorage } from "../../hooks/useLocalStorage/useLocalStorage";

type shoppingCartProvider = {
    children: ReactNode
};

type cartItem ={
    id: number
    quantity: number
};

type shoppingCartContext = {
    openCart: ()=>void
    closeCart: ()=>void
    getItemQuantity: (id: number) => number
    increaseCartQuantity: (id: number) => void
    decreaseCartQuantity: (id: number) => void
    removeFromCart: (id: number) => void
    cartQuantity: number
    cartItems: cartItem[]
};

const ShoppingCartContext = createContext({} as shoppingCartContext);

export function useShoppingCart(){
    return useContext(ShoppingCartContext);
}


export function ShoppingCartProvider({children}: shoppingCartProvider){

    const [isOpen, setIsopen] = useState(false);
    const [cartItems, setCartItems] = useLocalStorage<cartItem[]>("shopping-cart", []);

    const cartQuantity = cartItems.reduce((quantity, item) => item.quantity + quantity, 0);

    function getItemQuantity(id: number){
        return cartItems.find(item => item.id === id)?.quantity || 0;
    }

    function openCart(){
        setIsopen(true);
    }

    function closeCart(){
        setIsopen(false);
    }

    function increaseCartQuantity(id: number){
        setCartItems(currItems => {
            if(currItems.find(item => item.id === id) == null){
                return [...currItems, {id, quantity: 1}];
            }
            return currItems.map(item => {
                if(item.id === id){
                    return {...item, quantity: item.quantity + 1};
                }
                return item;
            });
        });
    }

    function decreaseCartQuantity(id: number){
        setCartItems(currItems => {
            if(currItems.find(item => item.id === id)?.quantity === 1){
                return currItems.filter(item=>item.id !== id);
            }
            return currItems.map(item => {
                if(item.id === id){
                    return {...item, quantity: item.quantity - 1};
                }
                return item;
            });
        });
    }

    function removeFromCart(id: number){
        setCartItems(currItems => {
            return currItems.filter(item => item.id !== id);
        });
    }

    return <ShoppingCartContext.Provider value={{
        openCart,
        closeCart,
        getItemQuantity, 
        increaseCartQuantity, 
        decreaseCartQuantity, 
        removeFromCart, 
        cartItems, 
        cartQuantity}
    
    }>
        {children}
        <ShoppingCart isOpen={isOpen}/>
    </ShoppingCartContext.Provider>
}