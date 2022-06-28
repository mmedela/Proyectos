
import { Container } from "react-bootstrap"
import {Routes, Route} from "react-router-dom"
import { About } from "./pages/about/About"
import { Home } from "./pages/home/Home"
import { Store } from "./pages/store/Store"

function App() {
 
  return (
    <Container className="mb-4">
      <Routes>
        <Route path="/" element={<Home/>}/> 
        <Route path="/store" element={<Store/>}/> 
        <Route path="/about" element={<About/>}/> 
      </Routes>
    </Container>
  )
}

export default App
