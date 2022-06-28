import { Offcanvas, Stack } from "react-bootstrap";
import { useShoppingCart } from "../../context/shopingCartContext/ShopingCartContext";
import { formatPrice } from "../../utils/FormatPrice";
import storeItems from "../../data/items.json";
import { CartItem } from "../cartItem/CartItem";

type shoppingCart = {
    isOpen: boolean
}

export function ShoppingCart({isOpen}: shoppingCart){
    const {closeCart, cartItems} = useShoppingCart();
    return <Offcanvas show={isOpen} onHide={closeCart} placement="end">
        <Offcanvas.Header closeButton>
            <Offcanvas.Title>Cart</Offcanvas.Title>
        </Offcanvas.Header>
        <Offcanvas.Body>
            <Stack gap={3}>
                {cartItems.map(item => (
                    <CartItem key={item.id} {...item} />
                ))}
                <div className="ms-auto fw-bold fs-5">
                    Total: {
                        formatPrice(cartItems.reduce((total, currItem) => {
                            const item = storeItems.find(i => i.id === currItem.id)
                            return total + (item?.price || 0) * currItem.quantity
                        }, 0))
                    }
                </div>
            </Stack>
        </Offcanvas.Body>
    </Offcanvas>
}