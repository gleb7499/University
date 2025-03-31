function toggleOtherColorInput() {
    var otherCuisineInput = document.getElementById('otherCuisineInput');
    var otherCuisineRadio = document.querySelector('input[name="cuisine"][value="Другая"]');
    if (otherCuisineRadio.checked) {
        otherCuisineInput.style.display = 'block';
        otherCuisineInput.setAttribute('required', '');
    } else {
        otherCuisineInput.style.display = 'none';
        otherCuisineInput.removeAttribute('required');
    }
}

function togglePhotoInput() {
    var photoInput = document.getElementById('photoInput');
    var modestyRadioNo = document.querySelector('input[name="modesty"][value="Да"]');
    if (modestyRadioNo.checked) {
        photoInput.classList.remove('hidden');
        photoInput.querySelector('input[type="file"]').setAttribute('required', '');
    } else {
        photoInput.classList.add('hidden');
        photoInput.querySelector('input[type="file"]').removeAttribute('required');
    }
}

function checkPhotoInput() {
    const photoInput = document.getElementById('photo');
    photoInput.addEventListener('input', () => {
        if (photoInput.files.length === 0) {
            photoInput.setCustomValidity('Вы должны добавить файл');
        } else if (!photoInput.files[0].type.startsWith('image/')) {
            photoInput.setCustomValidity('Файл должен быть изображением');
        } else {
            photoInput.setCustomValidity('');
        }
        const photoError = document.getElementById('photoError');
        photoError.textContent = photoInput.validationMessage;
    });
}

function setTodayDate() {
    var today = new Date().toISOString().split('T')[0];
    document.getElementById('todayDate').value = today;
}