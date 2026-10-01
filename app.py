import streamlit as st
import subprocess
import os

st.set_page_config(page_title="Codificador 6G", layout="centered")

st.title("📡 Sistema de Codificación 5G/6G")
st.markdown("Sube un archivo para analizar su entropía y comprimirlo usando LZW.")

# 1. Controles de la Interfaz
archivo_subido = st.file_uploader("Selecciona un archivo multimedia o de texto")
n_bits = st.selectbox("Tamaño de bloque (N bits)", [8, 64, 128, 512, 1024, 2048, 4096])

if st.button("Procesar Archivo"):
    if archivo_subido is not None:
        # Guardar el archivo subido en la carpeta data/
        ruta_guardado = os.path.join("data", archivo_subido.name)
        with open(ruta_guardado, "wb") as f:
            f.write(archivo_subido.getbuffer())
        
        st.info(f"Procesando {archivo_subido.name} con bloques de {n_bits} bits...")

        # 2. Conectar la Interfaz con el código C++
        
        comando = f"./codificador_6g '{ruta_guardado}' {n_bits}"
        resultado = subprocess.run(comando, shell=True, capture_output=True, text=True)

        # 3. Mostrar los resultados matemáticos
        if resultado.returncode == 0:
            st.success("¡Procesamiento exitoso!")
            st.text_area("Métricas de Shannon (Consola C++)", resultado.stdout, height=250)
            
            # Botones para descargar los resultados generados por C++
            with open("data/comprimido.bin", "rb") as file_comp:
                st.download_button("Descargar Archivo Comprimido", file_comp, file_name="comprimido.bin")
        else:
            st.error("Ocurrió un error en el núcleo de C++.")
            st.error(resultado.stderr)
    else:
        st.warning("Por favor, sube un archivo primero.")