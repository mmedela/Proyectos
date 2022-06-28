import { Col, Row } from "react-bootstrap"
import { StoreItem } from "../../components/storeItem/StoreItem"
import Items from "../../data/items.json"

export function Store() {
    return (
        <>
            <h1>Store</h1>
            <Row md={2} xs={1} lg={3} className="g-3">
                {Items.map(item =>(
                    <Col key={item.id}><StoreItem {...item}/></Col>
                ))}
            </Row>
        </>
    )
}