
import { Container } from "react-bootstrap"
import {Routes, Route} from "react-router-dom"
import { Navbar } from "./components/navbar/Navbar"
import { ShoppingCartProvider } from "./context/shopingCartContext/ShopingCartContext"
import { About } from "./pages/about/About"
import { Home } from "./pages/home/Home"
import { Store } from "./pages/store/Store"

function App() {
 
  return (
    <>
      <ShoppingCartProvider>
        <Navbar/>
        <Container className="mb-4">
          <Routes>
            <Route path="/" element={<Home />}/> 
            <Route path="/store" element={<Store />}/> 
            <Route path="/about" element={<About />}/> 
          </Routes>
        </Container>
      </ShoppingCartProvider>
    </>
  )
}

export default App
